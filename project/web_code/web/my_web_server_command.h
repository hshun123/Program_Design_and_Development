/**
 * @file my_web_server_command.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */
#ifndef WEB_MY_WEB_SERVER_COMMAND_H_
#define WEB_MY_WEB_SERVER_COMMAND_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>

#include "src/config_manager.h"
#include "web_code/web/visualization_simulator.h"

#include "web_code/web/my_web_server_session.h"
#include "web_code/web/my_web_server_session_state.h"
#include "web_code/web/my_web_server.h"
#include "src/data_structs.h"

class MyWebServerSession;
class MyWebServerSessionState;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for MyWebServerCommand.
 *
 * Inherites MyWebServerSession and MyWebServerSessionState. Declares execute
 * function which be ovverided by each command.
 */
class MyWebServerCommand {
 public:
  virtual ~MyWebServerCommand() {}
  virtual void execute(MyWebServerSession* session, picojson::value& command,
  MyWebServerSessionState* state) = 0;
};


///***** * * * * * COMMANDS * * * * * ******///

class GetRoutesCommand : public MyWebServerCommand {
 public:
      explicit GetRoutesCommand(MyWebServer* ws);
      void execute(MyWebServerSession* session, picojson::value& command,
      MyWebServerSessionState* state) override;
 private:
       MyWebServer* myWS;
};

class GetBussesCommand : public MyWebServerCommand {
 public:
      explicit GetBussesCommand(MyWebServer* ws);
      void execute(MyWebServerSession* session, picojson::value& command,
      MyWebServerSessionState* state) override;
 private:
        MyWebServer* myWS;
};

class StartCommand : public MyWebServerCommand {
 public:
        explicit StartCommand(VisualizationSimulator* sim);
        void execute(MyWebServerSession* session, picojson::value& command,
        MyWebServerSessionState* state) override;
 private:
        VisualizationSimulator* mySim;
        std::vector<int> timeBetweenBusses;
        int numTimeSteps;
};

// Eric Pause
/**
 * @brief The main class for PauseCommand.
 *
 * Inherites MyWebServerCommand. Define excute function which perform pause
 * and resume functionality
 */
class PauseCommand : public MyWebServerCommand {
 public:
			/**
		   * @brief constructor for Pause command
		   *
		   * @param[in] VisualizationSimulator* sim
		   *
		   */
        explicit PauseCommand(VisualizationSimulator* sim);
				/**
			 * @brief excute the pause command
			 *
			 * @param[in] MyWebServerSession* session
			 * @param[in] picojson::value& command
			 * @param[in] MyWebServerSessionState* state
			 *
			 */
        void execute(MyWebServerSession* session, picojson::value& command,
        MyWebServerSessionState* state) override;
 private:
        VisualizationSimulator* mySim;
};

class UpdateCommand : public MyWebServerCommand {
 public:
        explicit UpdateCommand(VisualizationSimulator* sim);
        void execute(MyWebServerSession* session, picojson::value& command,
        MyWebServerSessionState* state) override;
 private:
        VisualizationSimulator* mySim;
};

// Eric
/**
 * @brief The main class for AddListenerCommand.
 *
 * Inherites MyWebServerCommand. Define excute function which performs Adding
 * observers to the list.
 */
class AddListenerCommand : public MyWebServerCommand {
 public:
        /**
        * @brief constructor for AddListner command
        *
        * @param[in] VisualizationSimulator* sim
        *
        */
        explicit AddListenerCommand(VisualizationSimulator* sim);
        /**
        * @brief excute the AddListneer command
        *
        * @param[in] MyWebServerSession* session
        * @param[in] picojson::value& command
        * @param[in] MyWebServerSessionState* state
        *
        */
        void execute(MyWebServerSession* session, picojson::value& command,
        MyWebServerSessionState* state) override;
 private:
    VisualizationSimulator* mySim;
};

class InitRoutesCommand : public MyWebServerCommand {
 public:
        explicit InitRoutesCommand(ConfigManager* cm);
        void execute(MyWebServerSession* session, picojson::value& command,
        MyWebServerSessionState* state) override;
 private:
        ConfigManager* cm;
};

#endif  // WEB_MY_WEB_SERVER_COMMAND_H_
