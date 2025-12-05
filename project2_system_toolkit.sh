#!/bin/bash
calc_size(){ read -rp "path: " p; [[ -e "$p" ]] && du -sh "$p" || echo "not found"; }
count_processes(){ ps -e --no-headers | wc -l; }
login_duration(){ info=$(who -u am i); t=$(echo "$info"|awk '{print $3" "$4}'); now=$(date +%s); lt=$(date -d "$t" +%s); d=$((now-lt)); echo "$((d/3600))h $((d%3600/60))m"; }
file_age(){ read -rp "file: " f; [[ -f "$f" ]] || { echo "invalid"; return; }; now=$(date +%s); mt=$(stat -c %Y "$f"); echo "$(((now-mt)/86400)) days"; }
while true;do echo -e "1)size
2)proc
3)login
4)age
5)exit"; read -rp "choose:" c;
case $c in 1)calc_size;;2)count_processes;;3)login_duration;;4)file_age;;5)exit;; esac; done