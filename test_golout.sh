#!/bin/bash -x

LOUT="../../example"
# LOUT="../../clount/lout"

rm *.ps
pushd "doc"

  pushd "design"
    $LOUT -a -L -w all -o ../../design.ps
  popd
  pushd "user"
    $LOUT -a -L -w all -o ../../user.ps
  popd
  pushd "slides"
    $LOUT -a -L -w all -o ../../slides.ps
  popd
  pushd "expert"
    $LOUT -a -L -w all -o ../../expert.ps
  popd

popd
