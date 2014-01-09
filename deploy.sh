cp build/Chebble.pbw ../izqui.me/files/Chebble.pbw
cp html/chebble.html ../izqui.me/html/chebble.html
cd ../izqui.me
git commit -a -m "New Chebble binary"
git push vps master
cd ../Chebble