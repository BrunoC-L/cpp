# TCP Socket

## example

- see the usage of those files in client/server in <https://github.com/BrunoC-L/sfml-rs2d/tree/master/src>

## drawbacks

- having to use SFML (not that big of a drawback, but you can't just copy paste this in your code! ... unless you use SFML!)

- the use of "|END|" to identify that the message is done instead of sending packets, but at least you can send partial messages or 2 messages at once with this
