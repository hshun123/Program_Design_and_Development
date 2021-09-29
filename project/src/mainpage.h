// Copyright 2020 <Eric Hwang>

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage Bus Simulation
 *
 * \section intro_sec Introduction
 *
 *    Hello! Welcome to Transit Bus Simulator. This program is designed to run a simulator to demonstrate the behaviour of a Bus.
 *
 * \section UserGuide
 * Overview
 * This project is a Bus transit simulator that shows a simulation of Bus that travels around its given routes. These routes are composed of stops, of which the Bus would stop to either unload or load the passengers
 * depending on the Passenger’s destination. If there is no passeger at the stop and no passenger is unloading, the bus will skip the stop and continue going. There is a out-going route and a in-coming route. If the route is on outgoing route and the Bus has reached the last stop, the Bus switchs its routes
 * to the in-coming route. While if the route is an incoming route, the Bus would stop operating.
 *
 * The simulation shows multiple buses following along the first Bus. As the user, you will be able to start and pause/resume the simulation. You can press Start button on the bottom to start the simulation. And, press
 * Pause button to pause the simulation. If you wan to resume the simulation, you can re-click the Puase button which will be labled "Resume" after the first click.
 *
 * Below are main  steps for running the project
 *
 * **Step 1**:
 *
 * The first step is to obtain the codes and get use to it.
 *
 * The directory structure of this project:
 *
 *  **project**: directory that contains all the project subdirectories. The project subdirectories contain the source code, tests, executables, configuration file, and documentation for the transit simulator project.
 *
 *  **project/src**: Most of the source code (.cc AND .h files) for the transit simulation portion of the project is located here.
 *
 *  **project/src/makefile**: Used to create the simulation executable and executable 'driver' programs that can be used to regression test individual components
 *
 *  **project/drivers**: Contains the source code with the main function that is used to create the driver files for each of the major entitites being simulated by the transit simulation (substitute the name bus, stop, passengers, and route)
 *
 *  **project/web_code/web**: C++ source code for the web server used to enable communication between the visualization component of the vis_sim and the portion of the simulation that simulates the operation and activities of busses, passengers, stops and routes
 *
 *  **project/config**: contains the file config.txt used to specify the bus routes used by the transit simulation
 *
 * **Step 2**:
 *
 * The second step is to configure. In this program, you can add or change the routes you are going to use. Or, you can also use the given route. To add a new route, you should go to project/config directory.
 * You need to add your routes to the file **config.txt** in the directory. **Important** to notice that your route should include two routes which are out-going route and in-coming route. The start for the out-going route should be the end for the in-coming route, vise versa.
 * Each stop in the route should have its longitude and latitude of location. Besides, you also need to set the probability of generating a gassenger there.
 *
 * Example:
 *
 * STOP, Buford at Gortner Avenue, 44.984540, -93.181692, .01
 *
 * **Step 3**:
 *
 * The next step is to compile the program. One way to do this is to open Terminal and navigate to the location of where you stored the **project** directory. Then you should navigate to **src** directory inside. Once you are in the project/src directory, you should run the "make" command
 * on the terminal to compile the program. Example shown below:
 *
 * hwang241@csel-kh1250-16:/home/hwang241/3081_s20/repo-hwang241/project/src $ make
 *
 * Once you done, you will find executable vis_sim in **project/build/bin** directory. It means you have successfully complied the program.
 *
 * **Step 4**:
 *
 * The last step is to run the program. Navigate to **project** directory using terminal. Then, type the following command on the terminal: ./build/bin/vis_sim <port_number>
 *
 * <port_number> should be a number above 8000 that includes the last 3 digits of your student id
 * **So, if your student id number is: 1459345, use 8345, or 9345**
 *
 * Example:
 *
 * ```
 *  hwang241@csel-kh1250-16:/home/hwang241/3081_s20/repo-hwang241/project $ ./build/bin/vis_sim 8514
 * ```
 *
 * Once you type the command, run your browser and enter following address in the address bar
 *
 * ```
 * http://127.0.0.1:<port_number>/web_graphics/project.html
 * ```
 *
 * Now, you will see the simulator on the broswer. You can click on **Start** button to start the simulation. And, click **Pause** button to pause the simulator.
 *
 * This was a user guide to help everyday users run the Bus simulator. Thank you for your time!
 *
 * \section design_sec Design
 *
 * \subsection factory_design Factory Pattern
 *
 * For this iteration, I implemented a concrete bus factory rather than an abstract bus factory. For current iteration, it is not neccessary to use **Abstract Bus Factory**, but this might be midified later.
 * Below are the advantages and disadvantages of each factory implementation.
 *
 *  **Concrete Bus Factory**:
 *
 * **Pros**:
 *
 * Using a factory pattern in a project allows it to instantiate classes derived from a specific base class without needing to keep track of
 * the individual derived classes anywhere but the factory(McConnell). In this project, we need to generate buses depending on its capacity. It could be a small,
 * regular or large bus. Without using a factory, each time a new change is made, the client-side needs to keep track of those changes. For instance, if we add a
 * new bus type which is exLarge, we have to make a new corresponding change in the visualization_simulator file. However, bus factory patterns avoid this situation
 * from happening. We can simply add an X-Large subclass to inherit the bus class and add one more condition ladder in the concrete bus factory to reach the purpose.
 * So, the bus factory makes the code less coupled and easy to extend.
 *
 * **Cons**:
 *
 * There are also some potential disadvantages of using a concrete bus factory. One is that if we need to add several subtypes of the given buses, it is hard to implement.
 * It is hard to make different subtype instances of a bus type directly using a concrete bus factory. Also, it is difficult to use a different factory for generating buses.
 * Since the client expects an implementation of an interface but does not exactly know which bus type will the factory return. It makes it difficult for the client-side to make some specific changes to each type of bus.
 *
 *
 * **Abstract Bus Factory**:
 *
 * **Pros**:
 *
 * An abstract bus factory is a class with several different concrete factories. In this project, we can expect an abstract bus factory which extends the small bus factory,
 * regular bus factory, and the large bus factory which will specialize in corresponding bus classes. This type of implementation enables you to control the classes of bus objects the client creates using the abstract bus factory.
 * It also makes it easy to make changes for specific bus classes without affecting other bus types. For instance, if we want to change the way of generating buses for the small bus type. We can simply change the code in the small bus factory.
 * That way, it won’t affect the regular bus factory and the large bus factory.
 *
 * **Cons**:
 *
 * There are some disadvantages to using abstract bus factory implementation. First of all, it requires a more complex implementation which may lead to making it hard to understand the relationship between each class later.
 * A user may find it not easy to understand the code quickly. When a change is made in the abstract bus factory, all of its subclass which is concrete bus factories also need to make corresponding changes. For example,
 * if we modify the declaration of GenerateBus function, all the concrete bus factories need to modify their definitions.
 *
 * \section observer Designing and Implementing the Observer Pattern
 *
 * \subsection Observer Pattern in the project
 *
 * For this project, I designed and implemented Observert pattern for observing information about buses along their routes. As shown below, when the user click on the specific bus in the simulater, the information about the bus
 * shows up on the right side of the simulator. The information includes current position (longitude and latitude), number of passengers and the capacity of the bus. The user can then know the information about each bus proceeding
 * on each routes.
 *
 * \image html observer_pattern.png "Observer Pattern" width=1024px
 *
 * \subsection classes Classes and methods for Observer pattern
 *
 * To implement observer pattern in this project, I added new classes and methods.
 *
 * **IObserver**:
 *
 * IObserver class serves as Observer in the project. Observer is the user interface abstraction. It has a method named UpdateObserver which defines the action to be taken when the subject "Bus" provides new datas.
 *
 * **IObservable**:
 *
 * IObservable class serves as Subject in the project. IObservable maintaines the collection of observers which is the list of currently registered observers (bus). It has methods: RegisterObserver, ClearObservers, NotifyObservers.
 * RegisterObserver is a function to add observers bus in to the observer list while ClearObservers function is to remove buses from the list. NotifyObservers is called when there is a updated data and the observers needs to be notified
 * by new data.
 *
 * **BusWebObserver**:
 *
 * BusWebObserver class is a concrete class of IObserver. UpdateObserver is defined it this class which shows the information of the updated data of observer buses. The class is added in my_wev_server_command.cc file in web_code/web folder.
 *
 * **AddListener**:
 *
 * AddListener is a function delcared and defined in visualizetion_simulator file. This method is called when the observer bus has not been observed. Using specific bus id, it adds the bus in the simulation.
 *
 * **ClearListeners**:
 *
 * ClearListeners is a function delcared and defined in visualizetion_simulator file. This method is called when a bus is currently being observed. The function removes all observers in the simulation.
 *
 * \subsection challenges Challenges of implementing the pattern
 * The most difficult part of implemting observer pattern in Bus simulator is to understand the relationship between each class and find a actual way to connect those classes to share the datas.
 * Especially, implementing AddLisener and ClearListeners functions was difficult. Because, understaing how those functino are exactly working is not easy. But, thanks to the sources provided by
 * the course, I could find the way to complete the implementation. I will list the sources below for tips and advice on how to understand and implement the pattern in this project.
 *
 * Resources:
 * 1. https://www.geeksforgeeks.org/strategy-pattern-set-2
 * 2. Lab14 csci3081w
 * 3. The UML provided by the course.
 * \image html Observer_UML.jpg "UML" width=1024px
 *
 *
 *
 *
 *
 */

#endif  // SRC_MAINPAGE_H_
