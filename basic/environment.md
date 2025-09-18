---
title: School exercise environment
layout: main
section: basic
---

The goal of this step is for you to get familiar with the ESC working
environment and check that everything is correctly set up for the
school exercises.

If something doesn't work as expected, please ask one of the
organizers.

When using these computing resources you agree to comply with the "Regulation on
the use of INFN computing resources", available in
[Italian](https://www.cnaf.infn.it/wp-content/uploads/2020/03/Disciplinare_2020_IT.pdf)
and
[English](https://www.cnaf.infn.it/wp-content/uploads/2020/03/Disciplinare_2020_EN.pdf).
Please read also the "General information note on processing of personal data by
INFN", available in
[Italian](https://dpo.infn.it/wp-content/uploads/2019/01/Informativa_generale_INFN_181204.pdf)
and
[English](https://dpo.infn.it/wp-content/uploads/2020/07/Informativa_generale_181204_EN.pdf).

## Wi-Fi access

You can use either the `eduroam` or the `CeUB` Wi-Fi networks. For the latter
you should have received your personal credentials.

## SSH access to School computers

You have been assigned a personal account to access computing resources
hosted at INFN-CNAF. Credentials are that of your INFN AAI account.

To log on the computers prepared for the School, you have to go first
through the gateway host prepared for the school, named
`esc25.cloud.cnaf.infn.it`, with your AAI username.

```shell
[me@mylaptop ~]$ ssh username@esc25.cloud.cnaf.infn.it
username@esc25.cloud.cnaf.infn.it's password:
Last login: ...
[username@esc25-bastion ~]$
```

From `esc25-bastion` you can then log onto the School computers. There
are two servers available, named `esc25-a100-1` and `esc25-a100-2`. Both
are equipped with two nVidia A100 40GB GPUs, 32 CPU cores and 256 GB of
RAM.

The names of the machines can be tedious to type, but you can get around
it by creating a config file for ssh. With the ssh configuration **on
your laptop** you can also avoid the explicit jump through the
`esc25-bastion` host and forward the X11 display and the SSH agent.

```shell
[me@mylaptop ~]$ cat ~/.ssh/config
Host escbastion
  Hostname esc25.cloud.cnaf.infn.it
  User username

Host esc
  Hostname esc25-a100-1
  User username
  ProxyJump escbastion

Host *
  ForwardX11 yes
  ForwardAgent yes

[me@mylaptop ~]$ ssh esc
username@esc25-a100-1's password:
Last login: ...
[username@esc25-a100-1 ~]$
```

To further simplify the login to `esc`, you can use an SSH key. You first need
to create it (if you don't have one already), copy it remotely on both `esc25-bastion`
and `esc` and set it in your SSH configuration.

```shell
[me@mylaptop ~]$ ssh-keygen -C username@esc -f ~/.ssh/id_rsa_student_esc
Generating public/private rsa key pair.
...
[me@mylaptop ~]$ ssh-copy-id -i ~/.ssh/id_rsa_student_esc escbastion
/usr/bin/ssh-copy-id: INFO: Source of key(s) to be installed: "/home/me/.ssh/id_rsa_student_esc.pub"
...
username@esc25-a100-1's password: 
...
[me@mylaptop ~]$ ssh-copy-id -i ~/.ssh/id_rsa_student_esc esc
/usr/bin/ssh-copy-id: INFO: Source of key(s) to be installed: "/home/me/.ssh/id_rsa_student_esc.pub"
...
username@esc25-a100-1's password: 
...
[me@mylaptop ~]$ cat ~/.ssh/config
Host escbastion
  Hostname esc.cloud.cnaf.infn.it
  User username
  IdentityFile ~/.ssh/id_rsa_student_esc

Host esc
  Hostname esc25-a100-1
  User username
  IdentityFile ~/.ssh/id_rsa_student_esc
  ProxyJump escbastion

Host *
  ForwardX11 yes
  ForwardAgent yes
[me@mylaptop ~]$ ssh esc
Last login: ...
[username@esc25-a100-1 ~]$ 
```

Your shell is [`bash`](https://www.gnu.org/s/bash).

Please note that:

* The `esc25-bastion` host is useful and needed only as a gateway to
  `esc`. Don't execute heavy programs on it.
* Each `esc` computer is not assigned exclusively to a student.
* Your home directory is shared between all `esc` computers, including
  the `esc25-bastion`.
* Your home directory will be wiped out and your `username` account will
  be disabled soon after the end of the School. Please make sure to save
  somewhere else what you want to keep.

## School material

All the school hands-on material is included in a git repository. Get it using:

```shell
[username@esc25-a100-1 ~]$ git clone {{ site.github.clone_url }}
```

The repository contains also these pages.

## Enable the compiler

Log into `esc`, enable the use of `gcc 12.3` and check that it's available

```shell
[username@esc25-a100-1 ~]$ module load compilers/gcc-12.3_sl7
[username@esc25-a100-1 ~]$ gcc --version
gcc (GCC) 12.3.0
...
```

To guarantee that the module is always loaded in the environment, you can add
the `module load` in the shell initialization file.

```shell
[username@esc25-a100-1 ~]$ echo 'module load compilers/gcc-12.3_sl7' >> ${HOME}/.bashrc
```

## Install and test Google benchmark

Building and installing Google benchmark requires the cmake module;
however it is not necessary to enable cmake after Google benchmark has
been installed.

Download, build and install Google benchmark from the sources:
```shell
[username@esc25-a100-1 ]$ git clone https://github.com/google/benchmark.git
[username@esc25-a100-1 ]$ mkdir benchmark/build
[username@esc25-a100-1 ]$ cd benchmark/build
[username@esc25-a100-1 ]$ module load compilers/cmake-3.27.7
[username@esc25-a100-1 ]$ cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${HOME}/benchmark ..
[username@esc25-a100-1 ]$ make -j8 install
[username@esc25-a100-1 ]$ cd
[username@esc25-a100-1 ]$ export BENCHMARKROOT=${HOME}/benchmark
[username@esc25-a100-1 ]$ export CPATH=${CPATH}:${BENCHMARKROOT}/include
[username@esc25-a100-1 ]$ export LIBRARY_PATH=${LIBRARY_PATH}:${BENCHMARKROOT}/lib64
```

To execute the last commands automatically every time you log in, add
them at the end of your `.bashrc` file:

```shell
[username@esc25-a100-1 ~]$ cat >> ${HOME}/.bashrc << "@EOF"
export BENCHMARKROOT=${HOME}/benchmark
export CPATH=${CPATH}:${BENCHMARKROOT}/include
export LIBRARY_PATH=${LIBRARY_PATH}:${BENCHMARKROOT}/lib64
@EOF
```

To test that Google benchmark is correctly installed we can use a
[simple test program](https://github.com/google/benchmark?tab=readme-ov-file#basic-usage):

```c++
#include <benchmark/benchmark.h>

static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();
```

Save this program as `benchtest.cc`, compile it, and run it with:

```shell
[username@esc25-a100-1 ~]$ g++ -std=c++17 -O2 benchtest.cc -lbenchmark -pthread -o benchtest
[username@esc25-a100-1 ~]$ ./benchtest
```

You should see an output similar to:

```
2024-10-16T14:09:28+02:00
Running ./benchtest
Run on (80 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x40)
  L1 Instruction 32 KiB (x40)
  L2 Unified 1024 KiB (x40)
  L3 Unified 28160 KiB (x2)
Load Average: 1.54, 1.31, 0.78
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
------------------------------------------------------------
Benchmark                  Time             CPU   Iterations
------------------------------------------------------------
BM_StringCreation      0.000 ns        0.000 ns   1000000000000
BM_StringCopy           7.56 ns         7.56 ns     70446029
```

## Install oneAPI Threading Building Blocks

Download and install the latest release of oneAPI TBB:
```shell
[username@esc25-a100-1 ~]$ wget https://github.com/oneapi-src/oneTBB/releases/download/v2021.13.0/oneapi-tbb-2021.13.0-lin.tgz
[username@esc25-a100-1 ~]$ sha256sum oneapi-tbb-2021.13.0-lin.tgz
f5c9304710051f0193a07fb91b6d6ada5a3e0a6d623951ee176b1897816ecf4c  oneapi-tbb-2021.13.0-lin.tgz

[username@esc25-a100-1 ~]$ tar xaf oneapi-tbb-2021.13.0-lin.tgz
[username@esc25-a100-1 ~]$ ln -s oneapi-tbb-2021.13.0 tbb
[username@esc25-a100-1 ~]$ source ${HOME}/tbb/env/vars.sh
```

To execute the last command automatically every time you log in, add it to the end of your `.bashrc` file:
```shell
[username@esc25-a100-1 ~]$ echo 'source ${HOME}/tbb/env/vars.sh' >> ${HOME}/.bashrc
```

## Editing source code

### Editing locally

On `esc` you can find several editors available, such as `vim`, `emacs`, `nano`. If
the X display is available, graphical editors will open a window on your laptop;
the network latency however may not be good enough to give you a fine
experience. Just try.

### Editing remotely

The best option to edit files remotely is to use [Visual Studio
Code](https://code.visualstudio.com/) with its [remote development
extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack).

Alternatively you could edit the source code for the exercises on your laptop,
synchronizing them with the `esc` machine, for example using one of the
following:

* `scp`: You can copy files remotely using `scp`, in both directions.

* `sshfs`: You can mount your `esc` home directory on your laptop via `sshfs`.

* `rsync`: You can synchronize your local workspace with the one you keep on `esc`
  using [`rsync`](http://rsync.samba.org/). Please refer to the `rsync` manual to
  fully understand the meaning of the different options, so to avoid mistakes
  that could cause loss of data.

For all these options to work seamlessly, however, you should first simplify
your use of SSH to connect to `esc`, as described above.
