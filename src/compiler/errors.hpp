#ifndef __ERRORS_HPP__
	#define __ERRORS_HPP__

	namespace Y {
		namespace outputs {
			namespace errors {
				class Error {
				public:
					Error();
					~Error();
				};
			}
			namespace warnings {
				class Warning {
				public:
					Warning();
					~Warning();
				};
			}
			namespace informations {
				class Information {
				public:
					Information();
					~Information();
				};
			}
		}
	}
#endif