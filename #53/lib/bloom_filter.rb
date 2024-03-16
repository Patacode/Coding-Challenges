# frozen_string_literal: true

class BloomFilter
  attr_reader :size, :hash_function_count

  def initialize(datasource, epsilon: 0.1)
    line_qty = filesize(datasource)

    @size = required_bit_qty(line_qty, epsilon)
    @hash_function_count = optimal_hash_function_qty(@size, line_qty)
    @bit_array = init_bit_array(datasource)
  end

  def to_i
    @bit_array
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

  def init_bit_array(filepath)
    File.open(filepath) do |file|
      file
        .each_line
        .lazy
        .map { |line| compute_64bit_fnv1_hashes(line.strip) }
        .reduce(0) do |bit_array, hashes|
          hashes.reduce(bit_array) { |cbit_array, hash| cbit_array | 2**hash }
        end
    end
  end

  def compute_64bit_fnv1(string, offset_basis = nil)
    Hasher.fnv1(string, variant: 64, offset_basis: offset_basis)
  end

  def compute_64bit_fnv1_hashes(string)
    hashes = []
    offset_basis = nil

    @hash_function_count.times do
      new_hash = compute_64bit_fnv1(string, offset_basis)
      offset_basis = new_hash
      hashes << new_hash % @size
    end

    hashes
  end
end
