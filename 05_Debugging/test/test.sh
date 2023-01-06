scripts="test/gdb"
static="test/static"

gdb --batch --quiet --command "$scripts/gdb_script1" --args range \
    | grep @@@ \
    | cut -c 4- > gdb_script1.out
gdb --batch --quiet --command "$scripts/gdb_script2" --args range \
    | grep @@@ \
    | cut -c 4- > gdb_script2.out

cmp gdb_script1.out "$static/gdb_script1_ethalon"
cmp gdb_script2.out "$static/gdb_script2_ethalon"
