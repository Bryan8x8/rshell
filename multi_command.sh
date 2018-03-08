echo test && echo test2
ls -l && touch connectTest
ds || echo first command failed
pwd || echo this should not print
echo one && echo two && echo three && echo four || echo should not print
afd || vfvf || pwd && echo this should print
echo should print || echo should not print && echo should also print
nothing || nothing || nothing || echo testing chain of ORs
(echo a && echo b) || (echo c && echo d)
(echo a && echo b) && (echo c && echo d)
(echo a) && echo b
[ -f rshell.cpp ] && echo a
