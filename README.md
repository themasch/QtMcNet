QtMcNet
=======

Qt bindings for [libmcnet](https://github.com/deoxxa/libmcnet), an event
based, zero-copy, portable Minecraft network protocol parser.


current status
--------------
the parser seems to work (needs some testing/love). Thats it.

usage
-----
```C++
QMcParser parser();
connect(parser, SIGNAL(onPacket(mcnet_packet_t *)), something, SLOT(doSmthgWthPacket(mcnet_packet_t *)));
connect(parser, SIGNAL(onErroc(int)), something, SLOT(ohhNose(int)));
parser.start(socket);  // put in every opened QIODevice you like

// to "force" a read:
parser.readData();
```


License
-------
"THE BEER-WARE LICENSE" (Revision 42):
<masch@masch.it> wrote this file. As long as you retain this notice you
can do whatever you want with this stuff. If we meet some day, and you think
this stuff is worth it, you can buy me a beer in return.
