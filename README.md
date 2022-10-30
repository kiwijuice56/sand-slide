# godot-falling-sand
Prototype falling sand game made with Godot 4 beta 3 and GDextension. The full game can be downloaded for free at the [itch.io page](https://kiwijuice56.itch.io/sand-slide).
This repository is intended to serve as an example of using GDextension in a full project and to allow people to add new elements.

# Project Structure
This project was based on another open-source [template project](https://github.com/paddy-exe/GDExtensionSummator).

The majority of the game is implemented in C++ as a GDextension (in `extension\src`) that gets compiled into a dll file (in `game\bin`). 
The user interface was created in a godot project (in `game`) that calls methods from the GDextension as if it waas a node.

# Set Up
1. Clone/download the repository
2. Download the official `godot-cpp` [godot-cpp](https://github.com/godotengine/godot-cpp/tree/1044251a9e85e4c5cb484466c50f6cc309a1bfbe) and place it at the top of the directory alongside `game` and `extension`. 
Ensure that you install repository from the link, as compilation will only work if it is synced with Godot 4 beta 3. In addition, make sure that the project
is not open in another window while compiling.
3. In a command prompt at `godot-cpp`, run `scons` (and add `target=template_release` for exported projects). You only need to do this the first time you download the repository.
4. You are now ready to make changes to the project!

# Compiling changes
Compiling any changes is as simple as opening a command prompt at the root of the project directory and running `scons` (and adding `target=template_release` for exported projects). 
The dll inside of `game\bin` should be updated and require no further steps to run alongside the Godot project. 

# Creating New Elements
Each element is a class within `extension\src\elements` that inherits the `Element` class. 
To create your own element, create a new `.h` file and define a class with the name of your element.
Have your element inherit the `Element` class and implement the virtual methods `process`, `get_explode_resistance`, and `get_acid_resistance`. 

`process` contains the main logic for your element. Elements have no data or information associated with them, so `process` is essentially a static method that must infer
state from surrounding cells. You can get information and manipulate the simulation by calling methods from the `SandSimulation` pointer. Here is an example for sand:

```
const double FLAME = 1 / 64.0;p

void process(SandSimulation *sim, int row, int col) override {
	// randf is a helper method defined within element.h that returns a random number [0, 1)
	if (randf() < FLAME && sim->is_on_fire(row, col)) {
		// Set this cell to glass when on fire
		sim->set_cell(row, col, 25); // 25 is the ID of fire, as explained further below
		return;
	}
	// Otherwise, keep falling
	sim->move_and_swap(row, col, row + 1, col);
}
```

More methods helper methods for `SandSimulation` can be found in its header file.

`get_explode_resistance` and `get_acid_resistance` must return a float [0, 1] in which 0 is no resistance to explosions/acid and 1 is maximum resistance to explosions/acid.

When you are ready to add your element to the game, import the header file in `extension\src\sand_simulation.h` and add it to the `elements` vector in the constructor.
In the godot project, add your element name to the `ELEMENT_INDEX` list within `game\main.gd`. Finally, create a button with the matching name that you put within the list.
