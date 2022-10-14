#!/bin/bash
assert() {
  expected="$1"
  input="$2"

  ./suffix_array "$input" > tmp.s
  cc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => OK"
  else
    echo "$input => Failed"
    exit 1
  fi
}