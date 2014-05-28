Readme
======

This is a simple multithreaded webserver that serves up static content from the directory provided via command line.

Installation
============

To install, simply clone this repo recursively and build using Boost Build:

    git clone --recursive https://github.com/vmrob/webserver.git webserver
    cd webserver
    b2

Usage
=====

    ./webserver <document root>

