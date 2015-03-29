## Installing

First make sure you are in the `NodeShit` directory in your
terminal. Then run the following:

```sh
npm install
```

Wait for the libraries to be installed. 

## Running

Once everything is installed run the code by:

```sh
node bean-to-osc.js
```

## Important OSC Change

You will need to make one adjustment in the code that reads data
from the OSC port. 

As you may use more than one set of scratch data each OSC
'packet' will now have a number indicating the specific scratch
characteristic from which the data was sent. 

In `js` its an object: `[scratch, value]`. 

In OSC it should be represented as some type of array that
contains two integers. The first being 1, 2 or 3 indicating
which scratch the value comes from. The second is the value you
are used to getting from before.

## Adjusting the number of scratch areas to read from:

In `bean-to-osc.js` on line 16. Just add or remove scratch ids
from the object:

```js
var scratch = [scratchOne, scratchTwo];
```
