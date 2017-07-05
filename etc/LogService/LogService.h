#pragma once

namespace Veritas {
	namespace etc {
		class LogService {
			public:
                static void log(const char *format, ...);
                static void error(const char *format, ...);
                static void fatalError(const char *format, ...);
		};
	}
}
