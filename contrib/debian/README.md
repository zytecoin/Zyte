
Debian
====================
This directory contains files used to package zyted/zyte-qt
for Debian-based Linux systems. If you compile zyted/zyte-qt yourself, there are some useful files here.

## zyte: URI support ##


zyte-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install zyte-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your zyteqt binary to `/usr/bin`
and the `../../share/pixmaps/zyte128.png` to `/usr/share/pixmaps`

zyte-qt.protocol (KDE)

