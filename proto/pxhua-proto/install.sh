#!/bin/sh

#mvn install:install-file -DgroupId=com.qq.tars -DartifactId=tars-net -Dversion=1.7.0-SNAPSHOT -Dpackaging=jar -Dfile=tars-net-1.7.0-SNAPSHOT.jar

groupid='com.pxhua.video'
proj_name='pxhua-proto'
version='1.0.0'
file='target/pxhua-proto-${version}.jar'

mvn install:install-file -DgroupId=${groupid} -DartifactId=${proj_name} -Dversion=${version} -Dpackaging=jar -Dfile=${file}

