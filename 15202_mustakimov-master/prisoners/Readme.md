# Prisoner's dilemma
Prisoner's dilemma simulator for 3 prisoners.

## Modes
`--mode=mode`

 - **Detailed**: write `tick` or `tick n` to make 1 or n steps, `quit` to quit
 - **Fast**: strategies will decide *steps* times and result is printed
 - **Tournament**: all possible set of three strategies *steps* times and result is printed

To specify *steps*: `--steps=n`

## Matrix file format
`--matrix=file`

```
- d1 d2 d3
c0 c1 c2 -
```

dn - scores gained for deflecting, if n prisoners cooperate
cn - scores gained for cooperating, if n prisoners cooperate

## Config files
`--config=directory`

For some strategies you can specify custom configuration, it should be located in directory (default: ./config). Filename should be `strategyName-i.txt`, where i is index of strategy, starts from 1. If you have, for example, 2 random strategies and 1 democracy strategy, you should provide files random-1.txt, random-2.txt and democracy-1.txt