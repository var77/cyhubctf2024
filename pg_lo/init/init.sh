if [[ -z "${APP_USER_PASSWORD}" ]]; then
  echo "APP_USER_PASSWORD is required"
  exit 1
fi

psql -U postgres postgres -c "CREATE ROLE app_user WITH LOGIN PASSWORD '${APP_USER_PASSWORD}';"
psql -U postgres postgres -f /init.sql
