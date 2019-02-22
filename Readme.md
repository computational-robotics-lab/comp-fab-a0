# Assignement 0

Please fill in your name and student id

| First name: | Last name: | Student ID: |
| ----------- | ---------- | ----------- |
|             |            |             |

This assignement is to make sure your computer and you are both set up for the next three assignements. You do not have to hand-in anything. However, you can already play around with the code, and commit and push changes to your repository. For future assignements, you will have to commit and push your solutions to github. Commits (or rather pushes) after the deadline will be disregarded. So make sure you are ready and test out things with this assignement.

### Prerequisites
Make sure you install the following:

- Git (https://git-scm.com)
    + Windows: download installer from website
    + Linux: e.g. `sudo apt install git`
    + MacOS: e.g. `brew install git`
- CMake (https://cmake.org/)
    + Windows: download installer from website
    + Linux: e.g. `sudo apt install cmake`
    + MacOS: e.g. `brew install cmake`

### Building the code

On Windows, you can use Git Bash to perform the steps mentioned below.

> Note: There seems to be a github classroom bug, where the starter code is not imported. Thus, cancel the import process and import the code yourself, like so:
> After step 1: 
> 
> `cd comp-fab-a0-XXX`
> 
> `git pull https://github.com/computational-robotics-lab/comp-fab-a0` 
> 
> `git submodule update --init --recursive`

1. Clone this repository and load submodules:
    ```
    git clone --recurse-submodules YOUR_GIT_URL
    ```
2. Make build folder
    ```
    cd comp-fab-a0-XXX
    mkdir build && cd build
    ```
3. Compile code and run executable
    - for MacOS and Linux:
        ```
        cmake ..
        make
        ./src/app/app
        ```
    - for Windows: 
        * open `assignement0.sln` in Visual Studio
        * in the project explorer, right-click target "app" and set as startup app.
        * Hit F5!


### Some comments

- If you are new to git, there are many tutorials online, e.g. http://rogerdudler.github.io/git-guide/.

- You will not have to edit any CMake file, so no real understanding of CMake is required. You might however want to generate build files for your favorite editor/IDE: https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html
