#!/bin/bash
# Step 1: Install Dnsmasq on Ubuntu 22.04|20.04|18.04
sudo systemctl disable systemd-resolved
sudo systemctl stop systemd-resolved

# Remove the symlinked resolv.conf file
ls -lh /etc/resolv.conf
sudo unlink /etc/resolv.conf

# Then create new resolv.conf file.
echo nameserver 8.8.8.8 | sudo tee /etc/resolv.conf

# Dnsmasq is available on the apt repository, easy installation can be done by running:
sudo apt update
sudo apt install dnsmasq

# The main configuration file for Dnsmasq is /etc/dnsmasq.conf. Configure Dnsmasq by modifying this file
//sudo vim /etc/dnsmasq.conf
sudo cp dnsmasq.conf /etc/dnsmasq.conf

//If you want to enable DNSSEC validation and caching, uncomment
# sudo dnssec

# restart dnsmasq when done
sudo systemctl restart dnsmasq

# Step 2: Adding DNS records to Dnsmasq
# Add DNS records in the file./etc/hosts. Dnsmasq will reply to queries from clients using these records.
# sudo vim /etc/hosts
# 10.0.2.5	zoom.us
sudo cp hosts /etc/hosts

//You need to restart dnsmasq service after adding the records.
sudo systemctl restart dnsmasq

# Step 3: Testing Dnsmasq DNS functionality
# sudo vim /etc/resolv.conf
# nameserver 127.0.0.1
# nameserver 8.8.8.8
sudo cp resolv.conf /etc/resolv.conf

# Test using dig
dig A zoom.us


# Here is another example:
# You can confirm that we’re getting responses as configured.
dig zoom.us A +noall +answer



