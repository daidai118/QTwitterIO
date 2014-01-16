
About:
Twitter REST API wrapper for Qt. It reqires Qt5.


Configure:
Put QTwitterIO directory into your project folder and insert "include(./QTwitterIO/src/QTwitterIO.pro)" to your .pro file.


Usage:
First, instantiate QTwitterIO::TwitterIO with your consumer_key, consumer_secret, and parent QObject. 
Second, connect five signals of TwitterIO. They can be called only when Authentification.
Third, call initialize() of the instance. this function does OAuth.
Then, read https://dev.twitter.com/docs/api/1.1 and insert arguments of the APIs into QTwitterIO::QueryMap (which is typedef of QMap<QString,QString>), and call function of QTwitterIO::TwitterIO with the QueryMap instance as argument.
If you want to unlink application from Twitter Account, call unlink().

Bug report or question is more than wellcome.


Thanks:
o2 - OAuth library for Qt - https://github.com/pipacs/o2
