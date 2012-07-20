require 'matrix'

$result = []
exponent = Vector[1,1,1]
$executable = "build/2DVisualizer/2DVisualizer"

def exponent_to_argument(input)
  return input.map{|x| 2**x }.to_a.join(' ')
end

def sum(input)
  input.to_a.inject { |result, item| result + item }
end

def run_visualizer(input)
  $result << [`#{$executable} #{exponent_to_argument(input)}`, sum(input)].join(' ') + $/
end

8.times do
  run_visualizer(exponent)
  exponent = exponent + Vector[0,0,1]
  run_visualizer(exponent)
  exponent = exponent + Vector[0,1,0]
  run_visualizer(exponent)
  exponent = exponent + Vector[1,0,0]
end
run_visualizer(exponent)

print $result

