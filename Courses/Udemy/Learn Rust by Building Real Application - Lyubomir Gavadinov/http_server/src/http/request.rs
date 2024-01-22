use super::method::{Method, MethodError};
use super::{QueryParams, QueryParamsValue};
use std::convert::TryFrom;
use std::error::Error;
use std::fmt::{Debug, Display, Formatter, Result as fmtResult};
use std::str;
use std::str::{FromStr, Utf8Error};

#[derive(Debug)]
pub struct Request<'a> {
    method: Method,
    path: &'a str,
    query_params: Option<QueryParams<'a>>,
}

impl<'a> Request<'a> {
    pub fn path(&self) -> &str {
        &self.path
    }

    pub fn method(&self) -> &Method {
        &self.method
    }

    pub fn query_params(&self) -> Option<&QueryParams> {
        self.query_params.as_ref()
    }
}

impl<'a> TryFrom<&'a [u8]> for Request<'a> {
    type Error = ParseError;

    fn try_from(req: &'a [u8]) -> Result<Request<'a>, Self::Error> {
        let request = str::from_utf8(&req)?;
        let (method, request) = get_next_word(request).ok_or(ParseError::InvalidRequest)?;
        let (mut path, request) = get_next_word(request).ok_or(ParseError::InvalidRequest)?;
        let (protocol, _) = get_next_word(request).ok_or(ParseError::InvalidRequest)?;

        if protocol != "HTTP/1.1" {
            return Err(ParseError::InvalidProtocol);
        }
        let method = Method::from_str(method)?;

        let mut query_params = None;
        if let Some(idx) = path.find('?') {
            query_params = Some(QueryParams::from(&path[idx + 1..]));
            path = &path[..idx];
        }

        Ok(Self {
            method,
            path,
            query_params,
        })
    }
}

fn get_next_word(str: &str) -> Option<(&str, &str)> {
    for (idx, c) in str.chars().enumerate() {
        if c == ' ' || c == '\r' {
            return Some((&str[..idx], &str[idx + 1..]));
        }
    }
    None
}

pub enum ParseError {
    InvalidRequest,
    InvalidEncoding,
    InvalidMethod,
    InvalidProtocol,
}

impl ParseError {
    fn message(&self) -> &str {
        match &self {
            Self::InvalidRequest => "Invalid Request",
            Self::InvalidEncoding => "Invalid Encoding",
            Self::InvalidMethod => "Invalid Method",
            Self::InvalidProtocol => "Invalid Protocol",
        }
    }
}

impl Display for ParseError {
    fn fmt(&self, f: &mut Formatter) -> fmtResult {
        write!(f, "{}", self.message())
    }
}

impl Debug for ParseError {
    fn fmt(&self, f: &mut Formatter) -> fmtResult {
        write!(f, "{}", self.message())
    }
}
impl Error for ParseError {}

impl From<MethodError> for ParseError {
    fn from(value: MethodError) -> Self {
        ParseError::InvalidMethod
    }
}

impl From<Utf8Error> for ParseError {
    fn from(value: Utf8Error) -> Self {
        Self::InvalidEncoding
    }
}
