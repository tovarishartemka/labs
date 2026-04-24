#!/bin/bash

set -e

echo "== Switch to stg and update =="
git checkout stg
git pull origin stg

echo "== Switch to prd =="
git checkout prd

echo "== Merge stg into prd =="
git merge stg

TAG_NAME="prd_$(date +%Y%m%d_%H%M%S)"
echo "== Create tag $TAG_NAME =="
git tag -a "$TAG_NAME" -m "Auto sync stg to prd at $TAG_NAME"

echo "== Push prd and tags to origin =="
git push origin prd
git push origin --tags

echo "== Done =="
