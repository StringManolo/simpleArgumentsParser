source ./parseCLI 
parse_cli "$@"

exit() {
  local msg="$1"
  echo -e "$msg" 
  builtin exit 0
}

verbose=false;
if cli noArgs ;then                   exit "Arguments needed"; fi
if cli s h || cli c help ; then       exit "Help Menu:\n\nThis is just an example"; fi
if cli s v || cli c verbose ; then    verbose=true; fi
if cli c version ; then               exit "V0.0.1";  fi
if cli s s ; then                     echo "Hello!"; fi
if cli p found; then                  echo "Hello $(cli p)"; fi
if cli c debug-arguments; then        cli print; fi




: << JS_EXAMPLE_CODE
let verbose = false;
if (cli.noArgs)                  exit("Arguments needed");
if (cli.s.h || cli.c.help)       exit("Help Menu:\n\nThis is just an example");
if (cli.s.v || cli.c.verbose)    verbose = true;
if (cli.c.version)               exit("V0.0.1");
if (cli.s.s)                     console.log("Hello!");
if (cli.p)                       console.log("Hello", cli.p);
if (cli.c?.["debug-arguments"])  console.log(JSON.stringify(cli, null, 4));

const exit = msg => {
  console.log(msg);
  process.exit(0);
}
JS_EXAMPLE_CODE
