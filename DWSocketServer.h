/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 danielwpz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <functional>
#include <string>
#include "./ThreadPool/DWThreadPool.h"

#define E_LSN -1
#define E_BAD_HDL -2

typedef std::function<void(int, std::string)> SocketHandler;

class DWSocketServer 
{
private:
	DWThreadPool *pool;
	int listenfd, epollfd;
	SocketHandler handler;

public:
	DWSocketServer(short port);

	~DWSocketServer();

	/**
	 * Set the handler for socket events.
	 */
	int setHandler(SocketHandler handler);

	/**
	 * Start listening at the given port.
	 * Any incoming message will be delivered
	 * to user through registered callback
	 * function.
	 *
	 * Return: 0 if success
	 *		   < 0 if error
	 */
	int startup();		

	int shutdown();

	/**
	 * Specially-designed read and write.
	 */
	int sread(int fd, std::string **sptr);
	int swrite(int fd, const std::string &str);

private:
	void multiEpoll();
	void sclose(int fd);
};
