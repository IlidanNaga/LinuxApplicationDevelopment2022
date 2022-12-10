#!/bin/dash

# from assert.sh (https://github.com/torokmark/assert.sh)
RED=$(/bin/echo -en "\e[31m")
GREEN=$(/bin/echo -en "\e[32m")
NORMAL=$(/bin/echo -en "\e[00m")

log_failure() {
  printf "${RED}✖ %s${NORMAL}\n" "$@" >&2
}

log_success() {
  printf "${GREEN}✔ %s${NORMAL}\n" "$@" >&2
}

assert_eq() {
  local expected="$1"
  local actual="$2"
  local msg="${3-}"

  if [ "$expected" = "$actual" ]; then
    return 0
  else
    [ "${#msg}" -gt 0 ] && log_failure "$expected == $actual :: $msg" || true
    exit 1
  fi
}
# end from

sed_esub() {
  echo $3 | sed -E "s/$1/$2/"
}

name="repeating symbol"
assert_eq "$(./esub '(a*)' fff aab)" "$(sed_esub '(a*)' fff aab)" "$name"
log_success "$name"

name="capture group"
assert_eq "$(./esub '(a)(b)\1' fff aabaaaaa)" "$(sed_esub '(a)(b)\1' fff aabaaaaa)" "$name"
log_success "$name"
