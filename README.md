# VjGUI

That's very simple standalone GUI framework written purely in C++.

"Vj" stands for "Versatile justified".

# Documentation

## Setup

This framework is standalone so if you want to use a particular graphics API
you must create a class that inherits from an abstract class **Platform** and implement the following methods:

- DrawRect - draws a rectangle on a screen
- FillRect - draws a filled rectangle on a screen
- DrawText - draws a text on a screen
- DrawLine - draw a line between 2 points on the screen
- GetMousePos - returns a mouse position
- GetMouseButton - returns a current state of a mouse button
- GetKey - returns a state of a key
- IsCaps - checks whether caps is enabled or not
- GetDeltaTime - returns difference between last and current frames

Or if you use [defGameEngine](https://github.com/defGameEngine) there is **Platform_defGameEngine** class

Check **Example.cpp** to see how you integrate platform in your code

## Abilities

There are 6 types of components:

- Panel \
	Behaves like a window where you put all your GUI components

- Label \
	A box with a multi-lined text

- Button \
	A text label that you can press on and attach some event handlers

- Text entry \
	A text label where you have an ability to input some text

- List \
	A list of text labels that you can scroll around

- Slider \
	A numeric value multi-directional slider (e.g. used in a list component)
