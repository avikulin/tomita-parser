#
# Nicholas Yue nicholas_yue@users.sourceforge.net
#
# Note:
# (1) A dummy file include/config.h is required (remance from configure)
# (2) Default installation directory is /usr/local, override with -DCMAKE_INSTALL_PREFIX="" during cmake
#     invocation
# (3) Do the usual "make clean all" to build the library
# (4) To install either "make install" or "make install DESTDIR=<your directory>"
# (5) Need to include changes in include/log4cpp/Portability.hh for OSX to build

LIBRARY()

NOUTIL()
NO_COMPILER_WARNINGS()

SRCS(
  Appender.cpp
  AppenderSkeleton.cpp
  AppendersFactory.cpp
  BufferingAppender.cpp
  FactoryParams.cpp
  LayoutsFactory.cpp
  LevelEvaluator.cpp
  Localtime.cpp
  PassThroughLayout.cpp
  TriggeringEventEvaluatorFactory.cpp
  LayoutAppender.cpp
  FileAppender.cpp
  DailyRollingFileAppender.cpp
  RollingFileAppender.cpp
  FixedContextCategory.cpp
  IdsaAppender.cpp
  OstreamAppender.cpp
  StringQueueAppender.cpp
  SyslogAppender.cpp
  RemoteSyslogAppender.cpp
  SimpleLayout.cpp
  BasicLayout.cpp
  PatternLayout.cpp
  Category.cpp
  CategoryStream.cpp
  HierarchyMaintainer.cpp
  Configurator.cpp
  BasicConfigurator.cpp
  SimpleConfigurator.cpp
  PropertyConfigurator.cpp
  PropertyConfiguratorImpl.cpp
  LoggingEvent.cpp
  Priority.cpp
  NDC.cpp
  Filter.cpp
  TimeStamp.cpp
  StringUtil.cpp
  Properties.cpp
  Win32DebugAppender.cpp
  NTEventLogAppender.cpp
  DllMain.cpp
  DummyThreads.cpp
  MSThreads.cpp
  OmniThreads.cpp
  PThreads.cpp
  PortabilityImpl.cpp
  AbortAppender.cpp
)

END()