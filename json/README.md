# JSON

just JSON :)

you can use ' instead of " for strings! of course its not true json if you do that but it will parse fine with this class

which is nice because you can write your strings without having to do "\"something bla bla\"", just do "'something bla bla'"

I have not tried to make this efficient, but at least it avoids some copying here and there, if you are building LARGE jsons, this is probably NOT for you, I have not used move semantics to improve this, I know c++ has some default move constructors setup but I wouldn't be too hopeful on those being used since I defined my operator like operator= and I'm an idiot so they are all by VALUE!... I might come back and fix this later.
