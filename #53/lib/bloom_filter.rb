# frozen_string_literal: true

class BloomFilter
  attr_reader :size

  def initialize(datasource, epsilon: 0.1)
    @size = required_bit_qty(filesize(datasource), epsilon)
  end

  private

  def filesize(filepath)
    File.open(filepath) do |file|
      file.each_line.count
    end
  end

  def required_bit_qty(elem_qty, epsilon)
    -(elem_qty * Math.log(epsilon) / Math.log(2)**2).floor
  end
end
