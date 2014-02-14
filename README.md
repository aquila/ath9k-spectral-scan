WHAT IS THIS
============

Simple tool to visualise real-time spectral scan data from ath9k on Linux.

After playing with FFT_eval I decided to do something a little different.


REQUIREMENTS
============

 * ath9k and HW w/ spectral scan support
 * gnuplot (with X11 terminal support)
 * make, gcc
 * POSIX-shell
 * OSX: base64 installed with Homebrew for GNU compatibility
 * optional: ssh (in case you use remote machine to gather spectral scan)
 * optional: patched kernel and iw for scan chan-time parameter (http://thread.gmane.org/gmane.linux.kernel.wireless.general/111255 http://thread.gmane.org/gmane.linux.kernel.wireless.general/111251])


CONFIG
======

Before use you need to adjust the ./ss script. Read the comments in the file for more information.

The current ./ss script uses ssh to connect and issue commands to gather spectral scan data. This is because I have ath9k hooked up on a laptop but interact with my PC only. If you have ath9k hooked up locally you can skip the ssh dialing part and update interface/phy names only if necessary.


USAGE
=====

	make
	./ss


CREDITS
=======

The original code has been forked from ath9k-spectral-scan by Michał Kazior: 

	https://github.com/kazikcz/ath9k-spectral-scan

The formula has been taken from FFT_eval by Simon Wunderlich:

	https://github.com/simonwunderlich/FFT_eval

Inspired by:

	http://blog.altermundi.net/article/playing-with-ath9k-spectral-scan/
