/**
 * @file visualization_simulator.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */

#ifndef WEB_VISUALIZATION_SIMULATOR_H_
#define WEB_VISUALIZATION_SIMULATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <time.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <random>
#include <string>

#include "web_code/web/web_interface.h"
#include "src/config_manager.h"

class Route;
class Bus;
class Stop;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for visualization_simulator.
 *
 * Declares functions used for visualization_simulator. Member functions of the
 * class start the simulator, and update the bus status of the VisualizationSimulator
 * and pause/resume the simulator.
 *
 */
class VisualizationSimulator {
 public:
        VisualizationSimulator(WebInterface*, ConfigManager*);
        ~VisualizationSimulator();

        void Start(const std::vector<int>&, const int&);
        /**
       * @brief This is the update function to update the simulator
       *
       * This function will be used for udating the simulator purposes.
       */
        void Update();
        /**
       * @brief This is the pause function to pause/resume the simulator
       *
       * This function will be used for pause and resume the simulator purposes.
       */
        void Pause();  // Eric
        // ClearObservers
        /**
       * @brief This is the ClearListeners function to remove all bus observers
       * currently in the simulation
       *
       * This function will be used for clearing observers purposes.
       */
        void ClearListeners();

        // AddListener
        /**
       * @brief This is the AddListener function to add an specific bus observer
       * in the simulation which has not been observeds
       *
       * This function will be used for clearing observers purposes.
       */
        void AddListener(std::string* id, IObserver* observer);

 private:
        WebInterface* webInterface_;
        ConfigManager* configManager_;

        std::vector<int> busStartTimings_;
        std::vector<int> timeSinceLastBus_;
        int numTimeSteps_;
        int simulationTimeElapsed_;

        std::vector<Route *> prototypeRoutes_;
        std::vector<Bus *> busses_;

        int busId = 1000;
        int busType;  // bus type, used to figure type of bus.
};

#endif  // WEB_VISUALIZATION_SIMULATOR_H_
