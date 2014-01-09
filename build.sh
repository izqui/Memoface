echo "COMPILING JS"
cat js/*.js | uglifyjs -o src/js/pebble-js-app.js
echo "DONE COMPILING"