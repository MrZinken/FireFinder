defmodule Parser do
  use Platform.Parsing.Behaviour
  require Logger
  
  

  

  # Parse function to handle the payload
  def parse(<<battery::8, humidity::8, temperature::8, gas::8>>, meta) do
    %{
      battery: battery,
      humidity: humidity,
      temperature: temperature,
      gas: gas
    }
  end
end
