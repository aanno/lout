#!/bin/bash -x

IN=$1
shift
OUT=$1
shift

lout -a -L -w $IN -o $OUT.ps
# -S safe
gs -dPDFA -dBATCH -dNOPAUSE -sProcessColorModel=DeviceCMYK -sDEVICE=pdfwrite -sPDFACompatibilityPolicy=3 -sOutputFile=$OUT.pdf $OUT.ps 
evince $OUT.pdf

