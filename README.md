## Authors

[@kushagra](https://www.github.com/kushargs) (2019113020)

## Deployment

To deploy this project run

```bash
$ make
$ ./a.out
```

## Features

### PART 1

- Display- it promps the username and system_name with the curr_dir. Coded in prompt.c
- Builting commands cd, echo and pwd are inplemented in syscommnd.c
- ls is implemented with -a -l flags in ls.c .
- on default proccesses start in foreground. To run a background proccesses append the command by "&". implemented in othercommnd.c
- pinfo- displays the process-related info
- when background process exits there pid with exit status is printed in stderr.
- repeat command implemented.

### PART 2

- Input/output redirection
- Piping
- jobs (all the jobs with status R are running one other are denoted as stopped)
- sig
- fg
- bg
- ctrl-z (It stops the running process but unable to gain terminal cntl back)
- ctrl-c
- ctrl-d

- BONUS: 1. history 2. history extended 3. replay

## License

[MIT](https://choosealicense.com/licenses/mit/)
