<h1> <img src="./assets/icon.png"
  width="100"> 
</h1>

## Index

- [Index](#index)
- [Description](#description)
- [Usage](#usage)
- [Installation](#installation)
  - [Debian based:](#debian-based)
- [License](#license)

## Description

packc is a project manager for C++.
You can create project or add classes,source files, or header files to your existing packc project. 
In same time this files add to your cmake file automatically.
You can build and run your projects and define your own commands.

## Usage

Create Project:	packc create

Create Source File:	packc add -s \<<span style="color:red;">fileName</span>>

Create C++ Class:	packc add -c \<<span style="color:red;">fileName</span>>

Create Header File:	packc add -h \<<span style="color:red;">fileName</span>>

Add Dynamic Library: 	packc add -l \<<span style="color:red;">libraryName</span>>


Build Project:	 	packc build

Run Project:	 	packc run

Clean Project:	 	packc clean


## Installation

### Debian based:
- Go to [release](https://github.com/mehmetalicayhan/cppmac/releases/tag/v0.0.2) page and download .deb file

- Open a terminal and enter following command

```
  sudo dpkg -i <packageName>
```

## License
[MIT LICENSE](./LICENSE)