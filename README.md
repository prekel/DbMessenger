# DbMessenger

## Запуск через Compose

```sh
# Запуск базы и сборка клиента
docker compose up client -d
# Запуск клиента
docker compose exec client ./DbMessenger
```

## Сборка и запуск (legacy)

```shell script
make
./DbMessenger
```

### Зависимости

* postgresql
* ecpg (`sudo apt install libecpg-dev`)
* pgtypes
* max_prepared_transactions > 0
