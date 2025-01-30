echo $1
dseditgroup -o edit -a $1 -t user admin
dseditgroup -o edit -a $1 -t user wheel
