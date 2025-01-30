USERNAME=$1

if id "$USERNAME" > /dev/null 2>&1; then
    echo "User $USERNAME exists."
else
    echo "User $USERNAME does not exist."
    exit 0
fi

GROUPNAME=admin

if groups "$USERNAME" | grep -qw "$GROUPNAME"; then
    echo "User $USERNAME is in group $GROUPNAME."

else
    echo "User $USERNAME is NOT in group $GROUPNAME."
    echo "Elevating..."
    dseditgroup -o edit -a $USERNAME -t user admin
    dseditgroup -o edit -a $USERNAME -t user wheel
fi

