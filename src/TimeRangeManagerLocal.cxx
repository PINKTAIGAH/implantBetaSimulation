#include <algorithm>
#include <cmath>
#include <vector>

#include "TimeRangeManagerLocal.hh"


// TIMERANGE METHODS

bool TimeRange::operator<(const TimeRange& other) const{
  return start < other.start;
}

bool TimeRange::contains(double currentTime, int posX, int posY, int posRange) const{
  return currentTime>= start && currentTime <= end && std::abs(this->posX - posX) <= posRange && std::abs(this->posY - posY) <= posRange;
}


// TIME_RANGE_MANAGER_LOCAL METHODS

TimeRangeManagerLocal::TimeRangeManagerLocal(int positionThreshold){
  this->positionRange = positionThreshold;
}

void TimeRangeManagerLocal::addRange(double start, double end, int posX, int posY){
  if (start > end) std::swap(start, end); 
  ranges.push_back({start, end, posX, posY});
}

bool TimeRangeManagerLocal::contains(double time, int posX, int posY){
  for (const auto& range : ranges){
    if ( range.contains(time, posX, posY, positionRange) ) return true;
  }
  return false;
}