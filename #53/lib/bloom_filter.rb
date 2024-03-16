# frozen_string_literal: true

class BloomFilter
  attr_reader :size, :hash_function_count

  def initialize(datasource, epsilon: 0.1)
    line_qty = filesize(datasource)

    @size = required_bit_qty(line_qty, epsilon)
    @hash_function_count = optimal_hash_function_qty(@size, line_qty)
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

  def optimal_hash_function_qty(bit_qty, elem_qty)
    (bit_qty / elem_qty.to_f * Math.log(2)).ceil
  end
end
