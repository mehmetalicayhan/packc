<h1> <img src="./assets/icon.png"
  width="100"> 
</h1>

## Index

1. [Description](#description)
2. [Usage](#usage)
3. [Installation](#installation)
3. [Screenshots](#screenshots)
4. [License](#license)

## Description

packc is a project manager for C++.
You can create project or add classes,source files, or header files to your existing packc project. 
In same time this files add to your cmake file automatically.
You can build and run your projects and define your own commands.

## Usage

Create Project:	packc create

Create Source File:	packc add -s <filename>

Create C++ Class:	packc add -c <filename>

Create Header File:	packc add -h <filename>

Build Project:	 packc build

Run Project:	 packc run

Clean Project:	 packc clean

## Installation

### Debian based:
- Go to [release](https://github.com/mehmetalicayhan/cppmac/releases/tag/v0.0.2) page and download .deb file

- Open a terminal and enter following command

```
  sudo dpkg -i packc-0.0.2-beta.deb
```

## License
[MIT LICENSE](./LICENSE)