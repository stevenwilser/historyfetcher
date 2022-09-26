History Fetcher
===============

Version 0.9 - 2022 September 26

by Steven Wilser 
[stevenwilser.github.io](https://stevenwilser.github.io)

History Fetcher is a command-line linux program that parses the history data of Firefox and Chromium internet browsers and creates a txt or csv file containing the desired information for portable use. Available information includes: URL, URL Titles, Visit Count, Frecency (Firefox), and Last Visit Date.

Installation and Requirements
-----------------------------

History Fetcher requires g++, SQLite3, and must be run as root.

Clone repository:

    $ git clone https://github.com/stevenwilser/historyfetcher

Compile:

    $ make

Usage
-----

Run:

    $ sudo ./historyFetcherLauncher

or

    $ sudo bash historyFetcherLauncher
