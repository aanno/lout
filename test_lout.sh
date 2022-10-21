#!/bin/bash -x

rm *.ps
pushd "doc"

  pushd "design"
    lout -a -L -w all -o ../../design.ps
  popd
  pushd "user"
    lout -a -L -w all -o ../../user.ps
  popd
  pushd "slides"
    lout -a -L -w all -o ../../slides.ps
  popd
  pushd "expert"
    lout -a -L -w all -o ../../expert.ps
  popd


popd
