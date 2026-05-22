#!/bin/bash
# Скрипт для переноса изменений из dev в stg и prd
git checkout stg
git merge dev
git checkout prd
git merge stg
git checkout dev
echo "Деплой завершен: dev -> stg -> prd"
