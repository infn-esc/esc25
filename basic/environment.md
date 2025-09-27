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
  Hostname esc25.cloud.cnaf.infn.it
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

## Check the environment

Once logged into `esc`, verify that the environment is set up correctly:

```shell
[username@esc25-a100-1 ~]$ gcc --version
gcc (GCC) 11.5.0 20240719 (Red Hat 11.5.0-5)
...
[username@esc25-a100-1 ~]$ gdb --version
GNU gdb (AlmaLinux) 14.2-4.1.el9_6
...
[username@esc25-a100-1 ~]$ valgrind --version
valgrind-3.24.0
[username@esc25-a100-1 ~]$ scl enable gcc-toolset-14 -- gcc --version
gcc (GCC) 14.2.1 20250110 (Red Hat 14.2.1-7)
...
```

As you can see from the last command, beside the native compiler (gcc v. 11.5), there is also a more recent version (gcc v. 14.2), available through a so-called software collection.

To always work with the more recent version, enable the toolset in a new shell:

```shell
[username@esc25-a100-1 ~]$ scl enable gcc-toolset-14 bash
[username@esc25-a100-1 ~]$ gcc --version
gcc (GCC) 14.2.1 20250110 (Red Hat 14.2.1-7)
...
```

## Editing source code

### Editing locally

On `esc` you can find several editors available, such as `vim` and `emacs`. If
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
