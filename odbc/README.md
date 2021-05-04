# ODBC API

This is just some example code on how to interact with ODBC, its not that great and there MIGHT be a deadlock problem... so at your own risks, it might be in another part of my system but sometimes I experience deadlocks at startup. (of COURSE if I figure it out I will remove this warning and fix it if there was a problem here)

Make sure to add some layer of SQL injection protection in your application, personally mine is done at the socket message reception, not at the DB, some queries would be really hard to decipher whether they are malicious or not, where at least if you allow every query but filter what comes from the user when you get it, its less of a problem.

You can't copy paste the db.h/cpp directly because they use AbstractDB, you are not meant to just copy paste the entire thing, some of my methods are specific to my application, so just remove the imports and inheritance and keep what you want

Example use at <https://github.com/BrunoC-L/sfml-rs2d/tree/master/src/server/server>

## drawbacks

No concurrency!

Async operations but since there is no concurrency your operation is put at the end of a queue! it might be executed in a while

## TODO

add a thread pool to this...
