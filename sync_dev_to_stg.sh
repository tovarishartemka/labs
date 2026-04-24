#!/bin/bash

set -e

echo "== Switch to dev and update =="
git checkout dev
git pull origin dev

echo "== Switch to stg =="
git checkout stg

echo "== Merge dev into stg =="
git merge dev

TAG_NAME="stg_$(date +%Y%m%d_%H%M%S)"
echo "== Create tag $TAG_NAME =="
git tag -a "$TAG_NAME" -m "Auto sync dev to stg at $TAG_NAME"

echo "== Push stg and tags to origin =="
git push origin stg
git push origin --tags

echo "== Done =="

