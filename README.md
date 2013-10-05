Chebble
==========

(Just for geeks - Editing source code required)


Pebble app that looks like a watch but if you enter a button combination it shows some text.

### How do I change the text?

The text shown is hardcoded on porpuse in the source code in `text` variable. If you want to use you'll have to compile it yourself. 
Recomendation: Import project in CloudPebble, change the text and compile it from there. 

### How do combinations work?

Up and down buttons are used to 'enter' the combination and the center button is used to verify it, if the combination is correct it'll show the text, if it's not, it'll block the app and you'll need to quit and enter again.
You can set the combination using the `res` variable. You set an integer and then, starting from `0` it adds the result. The default value for the Up button is `+2` and for the Down is `-1`, but you can also customize it.

##### Example

If my combination is `9`, I would have to press 5 times the Up button and 1 time the Down button. If I get it wrong the app will get blocked.


**Disclaimer**: If you use it in a exam and they catch you, you don't fucking know me :)
