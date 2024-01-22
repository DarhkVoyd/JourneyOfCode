use crate::http::response::Response;
use crate::http::{request, ParseError, Request, StatusCode};
use std::io::{Read, Write};
use std::net::TcpListener;
pub struct Server {
    addr: String,
}

pub trait Handler {
    fn handle_request(&mut self, request: &Request) -> Response;

    fn handle_bad_request(&mut self, e: &ParseError) -> Response {
        println!("Failed to parse requet: {}", e);
        Response::new(StatusCode::BadRequest, None)
    }
}

impl Server {
    pub fn new(addr: String) -> Self {
        return Self { addr };
    }

    pub fn run(self, mut handler: impl Handler) {
        let listener = TcpListener::bind(&self.addr).unwrap();
        println!("Listening on {}", self.addr);

        loop {
            match listener.accept() {
                Ok((mut stream, _)) => {
                    let mut buffer = [0; 1024];
                    match stream.read(&mut buffer) {
                        Ok(_) => {
                            let response = match Request::try_from(&buffer as &[u8]) {
                                Ok(request) => handler.handle_request(&request),
                                Err(e) => {
                                    println!("Failed to parse request: {}", e);
                                    handler.handle_bad_request(&e)
                                }
                            };
                            response.send(&mut stream);
                        }
                        Err(e) => println!("Unable to read stream: {}", e),
                    }
                }
                Err(e) => println!("Unable to listen on the port: {}", e),
            }
        }
    }
}
