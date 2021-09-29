/**
 * @file visualization_simulator.cc
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */
#include "web_code/web/visualization_simulator.h"
#include <sstream>

#include "src/bus.h"
#include "src/route.h"
#include "src/concreteBus_factory.h"
#include "src/IObserver.h"

// global count, used to check if it is paused or resumed.
bool pausecheck = false;

VisualizationSimulator::VisualizationSimulator(WebInterface* webI,
  ConfigManager* configM) {
    webInterface_ = webI;
    configManager_ = configM;
}

VisualizationSimulator::~VisualizationSimulator() {
}

void VisualizationSimulator::Start(const std::vector<int>& busStartTimings,
  const int& numTimeSteps) {
    busStartTimings_ = busStartTimings;
    numTimeSteps_ = numTimeSteps;

    timeSinceLastBus_.resize(busStartTimings_.size());
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        timeSinceLastBus_[i] = 0;
    }

    simulationTimeElapsed_ = 0;

    prototypeRoutes_ = configManager_->GetRoutes();
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Report(std::cout);

        prototypeRoutes_[i]->UpdateRouteData();
        webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());
    }
}

// This function pause the simulator when the button show "pause,"
// and resume when the button is "resume."
void VisualizationSimulator::Pause() {
  std::cout <<"----------------pause pressed-------------------------"
  << std::endl;

  pausecheck = !pausecheck;  // toggles between true and false (pause&resume).
}

// This function update the status of bus and corresponding simulator.
// When the pause button is pressed, it stops updating. And, resume Updating
// when the button is pressed again and resume.
void VisualizationSimulator::Update() {
  // checks if pause button is clicked
  if (!pausecheck) {
    simulationTimeElapsed_++;

    std::cout << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
    std::cout << "~~~~~~~~~~" << std::endl;

    std::cout << "~~~~~~~~~~ Generating new busses if needed ";
    std::cout << "~~~~~~~~~~" << std::endl;

    // Check if we need to generate new busses
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        // Check if we need to make a new bus
        if (0 >= timeSinceLastBus_[i]) {
            Route * outbound = prototypeRoutes_[2 * i];
            Route * inbound = prototypeRoutes_[2 * i + 1];

            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type>
            dist1(1, 3);
            int rand_int = dist1(rng);
            busType = rand_int;
            // iteration 2
            // time_t rawtime;

            ConcreteBusFactory tmp;
            // generate bus using factory depends on bus type.
            busses_.push_back(tmp.ConcreteBusFactory::GenerateBus(
              std::to_string(busId), outbound->Clone(),
              inbound->Clone(), 1));
            busId++;

            timeSinceLastBus_[i] = busStartTimings_[i];
        } else {
            timeSinceLastBus_[i]--;
        }
    }

    std::cout << "~~~~~~~~~ Updating busses ";
    std::cout << "~~~~~~~~~" << std::endl;

    // Update busses
    for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
        busses_[i]->Update();

        if (busses_[i]->IsTripComplete()) {
            webInterface_->UpdateBus(busses_[i]->GetBusData(), true);
            busses_.erase(busses_.begin() + i);
            continue;
        }

        webInterface_->UpdateBus(busses_[i]->GetBusData());

        busses_[i]->Report(std::cout);
    }

    std::cout << "~~~~~~~~~ Updating routes ";
    std::cout << "~~~~~~~~~" << std::endl;
    // Update routes
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Update();

        webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());

        prototypeRoutes_[i]->Report(std::cout);
    }
  }
}

// Clear Listeners
void VisualizationSimulator::ClearListeners() {
  for (std::vector<Bus *>::iterator iter = busses_.begin();
  iter != busses_.end(); iter++) {
     (*iter) -> ClearObservers();
  }
}

// AddListener
void VisualizationSimulator::AddListener(std::string* id, IObserver* observer) {
  for (std::vector<Bus *>::iterator iter = busses_.begin();
  iter !=busses_.end(); ++iter) {
      if (((*iter) -> GetBusData().id) == (*id)) {
        (*iter)-> RegisterObserver(observer);
      }
    }
}
