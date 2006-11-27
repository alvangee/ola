/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * pluginadaptor.cpp
 * Provides a wrapper for the DeviceManager and Network objects so that the plugins
 * can register devices and file handles for events
 * Copyright (C) 2005  Simon Newton
 *
 * 
 */

#include <llad/pluginadaptor.h>
#include "devicemanager.h"
#include "network.h"

/*
 * Create a new pluginadaptor
 *
 * @param	dm	pointer to a devicemanager object
 * @param	net	pointer to the network object
 */
PluginAdaptor::PluginAdaptor(DeviceManager *dm, Network *net) {
	this->dm = dm ;
	this->net = net;
}

/*
 * register a fd
 *
 * @param fd		the file descriptor to register
 * @param dir		the direction we want
 * @param listener	the object to be notifies when the descriptor is ready
 * @param manager	the object to be notified if the listener returns an error
 *
 * @return 0 on success, non 0 on error
 */
int PluginAdaptor::register_fd(int fd, PluginAdaptor::Direction dir, FDListener *listener, FDManager *manager ) const {
	Network::Direction ndir = dir==PluginAdaptor::READ ? Network::READ : Network::WRITE ;
	return net->register_fd(fd,ndir,listener, manager) ;
}

/*
 * Unregister a fd
 *
 * @param fd	the file descriptor to unregister
 * @param dir	the direction we'll interested in
 *
 * @return 0 on success, non 0 on error
 */
int PluginAdaptor::unregister_fd(int fd, PluginAdaptor::Direction dir) const {
	Network::Direction ndir =  dir==PluginAdaptor::READ ? Network::READ : Network::WRITE ;
	return net->unregister_fd(fd,ndir) ;
}


/*
 * register a timeout
 *
 * @param second	the time between function calls
 *
 * @return the timeout id on success, 0 on error
 */
int PluginAdaptor::register_timeout(int seconds , TimeoutListener *listener ) const {
	return net->register_timeout(seconds, listener) ;
}



/*
 * Register a device
 *
 * @param dev	the device to register
 * @return 0 on success, non 0 on error
 */
int PluginAdaptor::register_device(Device *dev) const {
	return dm->register_device(dev) ;
}

/*
 * Unregister a device
 *
 * @param dev	the device to unregister
 * @return 0 on success, non 0 on error
 */
int PluginAdaptor::unregister_device(Device *dev) const {
	return dm->unregister_device(dev) ;
}

