use std::fmt::Display;

#[derive(Copy, Clone)]
pub enum StatusCode {
    OK = 200,
    BadRequest = 400,
    NotFound = 404
}

impl StatusCode {
   pub fn reason_phrase(&self) -> &str {
       match self {
           StatusCode::OK => "OK",
           StatusCode::BadRequest => "BadRequest",
           StatusCode::NotFound => "NotFound",
       }
   }
}

impl Display for StatusCode {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", *self as u16)
    }
}
