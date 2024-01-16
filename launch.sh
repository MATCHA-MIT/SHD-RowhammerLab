#!/bin/bash

if [ -z "$*" ]; then 
  echo "Executable argument required!"
  exit 0
fi

mkdir -p /condor_staging/$USER/

cp -r --no-preserve=mode,ownership . /condor_staging/$USER/
#chown -R ${USER}:${USER}_condor /condor_staging/$USER/*
#chmod -R +770 /condor_staging/$USER/*

cd /condor_staging/$USER/

condor_submit transfer_input_files=bin/${1} executable=scripts/${1}.sh log=${1}.log error=${1}.error output=${1}.out launch.condor

condor_wait ${1}.log
cd -

cp /condor_staging/$USER/${1}.log .
cp /condor_staging/$USER/${1}.out .
cp /condor_staging/$USER/${1}.error .

rm -rf /condor_staging/$USER/*
